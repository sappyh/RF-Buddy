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

#ifndef INCLUDED_ANNOTATOR_PACKET_ANNOTATOR_H
#define INCLUDED_ANNOTATOR_PACKET_ANNOTATOR_H

#include <annotator/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace annotator {

    /*!
     * \brief <+description of block+>
     * \ingroup annotator
     *
     */
    class ANNOTATOR_API packet_annotator : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<packet_annotator> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of annotator::packet_annotator.
       *
       * To avoid accidental use of raw pointers, annotator::packet_annotator's
       * constructor is in a private implementation
       * class. annotator::packet_annotator::make is the public interface for
       * creating new instances.
       */
      static sptr make(int nodeid, int id);
    };

  } // namespace annotator
} // namespace gr

#endif /* INCLUDED_ANNOTATOR_PACKET_ANNOTATOR_H */

