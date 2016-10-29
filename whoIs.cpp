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


  myFile.open("arp.txt");
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

  while (!packets.empty()) {
    if (packets.back().sIp == userIP && packets.back().sMac != userMAC) {

      //Regresa la MAC del atacante//
      cout<<packets.back().sMac;
      return true;
    }
    packets.pop_back();
  }
  return false;
}

int main() {
  vector<arpPacket> packets;
  packets = writePacketstoFile();

  isSpoofing(packets,"10.189.15.142","e1:c1:81:01:f1:c1");
}
