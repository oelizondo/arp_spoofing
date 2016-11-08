from scapy.all import *

THRESHOLD = 8
packets = {}

victim_ip = None
mac_victim = None
attacker_mac = None

flag = False
format_answer = "\n"

def wait_for_answer(packet):
    global format_answer
    format_answer += ("MAC of victim: " + packet.hwsrc + '\n')
    print(format_answer)
    exit()

def buildPacket(ip):
    mypacket = Ether()/ARP()
    mypacket.op = 1 #request
    mypacket.psrc="192.168.0.165" #IP DEL HOST
    mypacket.hwdst="ff:ff:ff:ff:ff:ff" # all victims
    mypacket.pdst = ip # IP DE LA VICTIMA
    mypacket.dst = "ff:ff:ff:ff:ff:ff" # all victims
    return mypacket

def check_for_and_add(packet, key):
    try:
        packet[key] += 1
    except:
        packet[key] = 0

def arp_traffic(packet):
    if packet[ARP].op == 2: #is-at (response)
        key = packet[ARP].hwsrc +  packet[ARP].psrc
        check_for_and_add(packets, key)

        if flag and packet[ARP].psrc == victim_ip and packet[ARP].hwsrc != attacker_mac:
            wait_for_answer(packet[ARP])

        if packets[key] >= THRESHOLD:
            global flag
            flag = True
            global format_answer
            format_answer += ("Attacker\'s MAC: " + packet[ARP].hwsrc + '\n' + "Victim\'s IP: " + packet[ARP].psrc + '\n')
            #print("Attacker\'s MAC: " + packet[ARP].hwsrc)
            #print("Victim\'s IP: " + packet[ARP].psrc)
            global victim_ip
            global attacker_mac
            attacker_mac = packet[ARP].hwsrc
            victim_ip = packet[ARP].psrc
            arp_request_packet = buildPacket(packet[ARP].psrc)
            sendp(arp_request_packet, loop =1, inter = .2, count = 1)

        else:
            print("Don't worry, be happy")




print sniff(prn=arp_traffic, filter="arp", store=0, count=200)
