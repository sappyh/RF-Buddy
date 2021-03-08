/* -*- c++ -*- */
/*
 * Copyright 2020 Saptarshi.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "packet_annotator_impl.h"

namespace gr
{
namespace annotator
{

packet_annotator::sptr
packet_annotator::make(int nodeid, int id)
{
  return gnuradio::get_initial_sptr(new packet_annotator_impl(nodeid, id));
}

/*
     * The private constructor
     */
packet_annotator_impl::packet_annotator_impl(int nodeid, int id)
    : gr::block("packet_annotator",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)),
      d_nodeid(nodeid), d_id(id)
{
  message_port_register_in(pmt::mp("message"));
  message_port_register_out(pmt::mp("annotations"));
  d_count.store(0);

  set_msg_handler(pmt::mp("message"), boost::bind(&packet_annotator_impl ::create_annotations, this, _1));
}

/*
     * Our virtual destructor.
     */
packet_annotator_impl::~packet_annotator_impl()
{
}

void packet_annotator_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required)
{
  /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
}

void packet_annotator_impl::create_annotations(const pmt::pmt_t message)
{
  //Get the CDR and CAR from the PMT Messages
  pmt::pmt_t car = pmt::car(message);
  pmt::pmt_t cdr = pmt::cdr(message);
  //CAR has the dict for the sample begin and count fields.
  if (!pmt::is_dict(car))
  {
    GR_LOG_WARN(d_logger, boost::format("CAR is not a dict"));
    return;
  }
  else
  {
    sample_start = pmt::dict_ref(car, pmt::mp("sample_start"), pmt::get_PMT_NIL());
    sample_count = pmt::dict_ref(car, pmt::mp("sample_count"), pmt::get_PMT_NIL());
    lqi = pmt::dict_ref(car, pmt::mp("lqi"), pmt::get_PMT_NIL());
    if (pmt::eqv(sample_start, pmt::get_PMT_NIL()))
    {
      GR_LOG_ERROR(d_logger, boost::format("Sample start key not found in dict"));
      return;
    }
    else if (pmt::eqv(sample_count, pmt::get_PMT_NIL()))
    {
      GR_LOG_ERROR(d_logger, boost::format("Sample count key not found in dict"));
      return;
    }
  }

  //CDR has the node MAC
  //Bytes 7-8 have the source mac which we will compare to the
  uint8_t *payload = (uint8_t *)pmt::blob_data(cdr);
  int received_nodeid = payload[7] << 8 | payload[8];
  // printf("Received from : %d and d_id is %d \n", received_nodeid, d_id);

  //Create annotation that can be send as an command to the sigmf sink.

  // if (received_nodeid == d_id)
  // {

    GR_LOG_INFO(d_logger, boost::format("Received : %d") % d_count);

    //Send global meta packet on the first message
    if (d_count.load() == 0)
    {
      pmt::pmt_t meta = pmt::make_dict();
      // |COMMAND| set_global_meta
      meta = pmt::dict_add(meta, pmt::mp ("command"), pmt::mp("set_global_meta"));
      // |KEY| rfbuddy: nodeid  
      meta = pmt::dict_add(meta, pmt::mp ("key"), pmt::mp("rfbuddy:nodeid"));
      // |Val| d_nodeid
      meta = pmt::dict_add(meta, pmt::mp ("val"), pmt::mp(d_nodeid));

      //Publish the message
      message_port_pub(pmt::mp("annotations"), meta);
    }

    //Send annotation packet on every message
    //Has to be a dictionary
    pmt::pmt_t annotation = pmt::make_dict();
    // |COMMAND| set_annotation_meta
    annotation = pmt::dict_add(annotation, pmt::mp("command"), pmt::mp("set_annotation_meta"));
    // |sample_start|
    annotation = pmt::dict_add(annotation, pmt::mp("sample_start"), sample_start);
    // |sample_count|
    annotation = pmt::dict_add(annotation, pmt::mp("sample_count"), sample_count);
    // |key| rfbuddy: messageid
    annotation = pmt::dict_add(annotation, pmt::mp("key"), pmt::mp("rfbuddy:messageid"));
    // |Val| message_count
    annotation = pmt::dict_add(annotation, pmt::mp("val"), pmt::mp(d_count++));
     // |key| rfbuddy: messageid
    annotation = pmt::dict_add(annotation, pmt::mp("key"), pmt::mp("rfbuddy:lqi"));
    // |Val| message_count
    annotation = pmt::dict_add(annotation, pmt::mp("val"), lqi);

    message_port_pub(pmt::mp("annotations"), annotation);
  // }
}

int packet_annotator_impl::general_work(int noutput_items,
                                        gr_vector_int &ninput_items,
                                        gr_vector_const_void_star &input_items,
                                        gr_vector_void_star &output_items)
{
  return 0;
}

} /* namespace annotator */
} /* namespace gr */
