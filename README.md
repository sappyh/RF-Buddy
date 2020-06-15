# RF-Buddy

## SigMF
The block records signals in SigMF format (https://github.com/gnuradio/SigMF)


## Project Structure
The project has two main sub directories: Code and Paper

### Code 
The code includes:
- GNU Radio blocks: 
    - gr-ieee-802154: This has the modified 802154 decoder (packet_decoder block), which allows it annotate, where a 15.4 message is starting and where a 15.4 message is ending. It does so, by tracking the states of the 15.4 decoder 
    - gr-annotator: This is the block, that takes in the annotated messages and converts them to the gr-sigmf annotation blocks for the SigMF block.
    - gr-sigMF: The SigMF block takes the annotations from the gr-annotator block and writes them to the sigmf metadata for the recording. It also takes in the data stream and writes it to the sigmf data file for the recording.
- Hierarchical flowgraphs:
    - 154RX.grc: 802.15.4 RX PHY block
    - 154TX.grc: 802.15.4 TX PHY block
- Python executables:
    - data_collector_final: Running this starts the capture process from the USRP and generates the SigMF recording
    - file_collector: You can also capture the USRP recording using file sink. Then you can use this to playback those data recordings to create the SigMF recordings using this python script

## Running the data collector
In order to run the data collector script, you need to configure the script with the following parameters:
``self.annotator_packet_annotator_0 = annotator.packet_annotator(1, 1)
  self.sigmf_sink_0 = gr_sigmf.sink("cf32", 'node-1', gr_sigmf.sigmf_time_mode_relative, False)``
### packet annotater(node_id, id)
- node_id: the MAC id for the node transmitting the message
- id: the distinct id you use to identify the node

### gr_sigmf.sink("cf32", 'node-1', gr_sigmf.sigmf_time_mode_relative, False)
- 'node-1' : the file name you want the recording to be in
