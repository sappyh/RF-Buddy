## Experimental Plan for verifying if we can distinguish between devices just based on their RF transmissions

### Context:

Massive scale of IoT devices which will monitor and control every kind of environment around us, whether its home, office, transport, industry. This close interconnection of IoT devices with our day to day life mandates security of these devices, need to taken into account seriously  because of the massive scale of deployments. But IoT devices are mostly resource constrained and cannot incorporate the complex cryptographic functions. But these devices have inherent uniqueness which is provided by the hardware imperfections. If we move the authentication task to the IoT gateway is the inherent uniqueness detectable in the way they communicate?

RF fingerprinting techniques try to address these challenges and have shown that it is indeed possible to detect the instrinsic characteristics of devices from just the RF transmitted signals.

### Prior Art and Questions: 

**Technology specific and Technology Agnostic techniques**

There have been studies in both radio technology specific fingerprinting as well as technology agnostic fingerprinting techniques. Technology specific fingerprinting techniques rely on proper feature selection and feature extraction such as CFO and Phase Errors. Whereas, technology agnostic fingerprinting  techniques are enabled by use of deep neural networks with large quantities of RF signal data. Another key difference between the two is the use of specialized hardware in technology agnostic fingerprinting techniques whereas technology specific techniques can work without them. 

**Q1**: *Which technique among the technology agnostic and technology specific techniques requires more data and what is the speed of inference or identification in both cases?*

**Q2**: *Which of these two techniques are more impacted by environmental variations?*



**Impact of dynamic channel environment**

Most of the prior studies have only considered static channels. Few studies have highlighted the difficulty of  distinguishing the radios studied in different locations and different times. So a important aspect of the selected fingerprinting technique should be it should be robust to channel variations.

**Q3:** *How to circumvent the effect of the dynamic channel conditions in the selected fingerprinting technique?*

I think the core question to this one is *What can only the transmitter do, that the channel can't?*  One idea I have is since the most common error is in the quadrature mixer and the power amplifier. Can we design a payload, that stretches these error to the max it can be then we can probably see the specific variations even inspite of possible channel variations. If we can design such a payload that clearly amplifies the errors for one technology, we can probably design it for other technologies too. The question I want to ask here is: *Is the signature similar for all the symbols or particular symbols show the signature more prominently?* or maybe combination these effects are more pronounced when the transmitter switches from one symbol to the next, in that case *What is the transition of symbols which causes makes the inherent features of the transmitter more pronounced?*

If we can find such a combination, we can put those symbols as the security header for the MAC, then it easily integrates into the communication standard.



**Applicability of these techniques to deployment scenarios**

All the studies so far have tried to address the problem of RF fingerprinting with a database of known signatures so its very hard to extend the network posing serious scalability challenges. Can we design a technique that is able to extend this database on the fly with minimum messaging to autheticate a node in a network. Essentially what we need is a technique that is able to do the fingerprinting with less data.



**Generality to the receiver**

**Q:** *Is the fingerprinting technique developed robust enough to the choice of receiver? Or is the accuracy effected by this choice?*



### Problem:

In my study I want to focus on design of a fingerprinting technique that is able to able to do the fingerprinting with less data. This allows us to scale the network taking into account practical deployment scenarios.

### Method:

**Important Considerations:**

- The data should be identical in content across the nodes



**Feasibility Study 1:**

- Collect the data for different nodes.
  - Collected 100 messages per node for Zolertia Firefly
- Create an input method for organizing the data into data blocks for the analysis
- Do a time series analysis of the data
  - 80/20 train-test split
  - 60/20 train-validation split

*Questions I need to answer:*

- How much data do I need to train the model accurately
  - Accuracy vs number of samples
  - Helps in understanding the tradeoff of the network in these tasks.
- What kind of preprocessing steps I would need for better training accuracy
  - SNR variations for robustness to channel conditions.
  - How to segment the data to feed into these networks? 
    - Split by symbols or window it across symbol transitions for these networks?



*Action Plan:*

1. Create the python module for sigMF datafiles.
2. Create a python module for splitting the data in the file into different training samples.



**Next Plans:**

- Once this feasibility study is done, we can try to see if this network can be used in a Siamese architecture, which is the ultimate goal of this project.







