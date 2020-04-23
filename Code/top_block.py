#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Top Block
# GNU Radio version: 3.8.1.0

import os
import sys
sys.path.append(os.environ.get('GRC_HIER_PATH', os.path.expanduser('~/.grc_gnuradio')))

from IEEE154RX import IEEE154RX  # grc-generated hier_block
from gnuradio import analog
from gnuradio import blocks
from gnuradio import gr
from gnuradio.filter import firdes
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio import uhd
import time
import foo

class top_block(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 4e6

        ##################################################
        # Blocks
        ##################################################
        self.uhd_usrp_source_0 = uhd.usrp_source(
            ",".join(("", "")),
            uhd.stream_args(
                cpu_format="fc32",
                args='',
                channels=list(range(0,1)),
            ),
        )
        self.uhd_usrp_source_0.set_center_freq(2.48e9, 0)
        self.uhd_usrp_source_0.set_normalized_gain(0.5, 0)
        self.uhd_usrp_source_0.set_antenna('RX2', 0)
        self.uhd_usrp_source_0.set_bandwidth(5e6, 0)
        self.uhd_usrp_source_0.set_samp_rate(samp_rate)
        self.uhd_usrp_source_0.set_time_now(uhd.time_spec(time.time()), uhd.ALL_MBOARDS)
        self.foo_wireshark_connector_0 = foo.wireshark_connector(195, False)
        self.blocks_tag_gate_0 = blocks.tag_gate(gr.sizeof_gr_complex * 1, False)
        self.blocks_tag_gate_0.set_single_key("")
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, '/home/saptarshi/Desktop/Papers/RF-Buddy/Code/capture.pcap', False)
        self.blocks_file_sink_0.set_unbuffered(True)
        self.analog_pwr_squelch_xx_0 = analog.pwr_squelch_cc(-25, 1e-4, 0, True)
        self.IEEE154RX_0 = IEEE154RX()



        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.IEEE154RX_0, 'rxout'), (self.foo_wireshark_connector_0, 'in'))
        self.connect((self.analog_pwr_squelch_xx_0, 0), (self.blocks_tag_gate_0, 0))
        self.connect((self.blocks_tag_gate_0, 0), (self.IEEE154RX_0, 0))
        self.connect((self.foo_wireshark_connector_0, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.uhd_usrp_source_0, 0), (self.analog_pwr_squelch_xx_0, 0))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.uhd_usrp_source_0.set_samp_rate(self.samp_rate)



def main(top_block_cls=top_block, options=None):
    if gr.enable_realtime_scheduling() != gr.RT_OK:
        print("Error: failed to enable real-time scheduling.")
    tb = top_block_cls()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()
        sys.exit(0)

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    tb.start()
    try:
        input('Press Enter to quit: ')
    except EOFError:
        pass
    tb.stop()
    tb.wait()


if __name__ == '__main__':
    main()
