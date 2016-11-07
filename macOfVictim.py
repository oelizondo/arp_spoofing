## Import Scapy module
from scapy.all import *


ip = input("Type the IP address of the victim: -> ")
print("You are looking for the mac of this IP " + ip);


packet = Ether()/ARP()
packet.op = 1 #request
packet.psrc="10.15.90.211" #IP DEL HOST
packet.hwdst="ff:ff:ff:ff:ff:ff" # all victims
packet.pdst = ip # IP DE LA VICTIMA
packet.dst = "ff:ff:ff:ff:ff:ff" # all victims

#packet.show()

sendp(packet, loop =1, inter = .2, count = 1)
