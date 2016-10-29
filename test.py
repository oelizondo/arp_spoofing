## Import Scapy module
from scapy.all import *

file = open("arp.txt", "w")

def arp_traffic(packet):
    #if packet[ARP].op == 1: #who-has (request)
        #file.write("1 " + packet[ARP].psrc + " " + packet[ARP].pdst + '\n')
        #return "Request: " + packet[ARP].psrc + " is asking about " + packet[ARP].pdst

    if packet[ARP].op == 2: #is-at (response)
        file.write("2 " + packet[ARP].hwsrc + " " + packet[ARP].psrc + '\n')
        return "*ARP Replay: " + packet[ARP].hwsrc + " has address " + packet[ARP].psrc

print sniff(prn=arp_traffic, filter="arp", store=0, count=10)
