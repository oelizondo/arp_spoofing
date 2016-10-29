#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct arpPacket{
  string option;
  string sMac;
  string sIp;
};


vector<arpPacket> writePacketstoFile() {
  vector<arpPacket> packets;
  ifstream myFile;
  string fileName = "arp.txt";

  myFile.open(fileName);
  string sOption;
  string sMac;
  string sIp;
  arpPacket aux;

  while (myFile >> sOption >> sMac >> sIp) {
    aux.option = sOption;
    aux.sMac = sMac;
    aux.sIp = sIp;
    packets.push_back(aux);
  }

  myFile.close();

  return packets;
}

bool isSpoofing (vector<arpPacket> packets,string userIP,string userMAC) {

  while (packets) {
    if packets.back().sIp == userIP && packets.back().Mac != userMac {
      true;
    }
    packets.pop_back()
  }
  return false;
}

int main() {
  vector<arpPacket> packets;
  packets = writePacketstoFile();
}
