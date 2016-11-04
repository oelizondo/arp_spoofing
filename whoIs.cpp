#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct arpPacket{
  string option;
  string sMac;
  string sIp;
};

const int THRESHOLD = 10;

int optionDirfference(vector<arpPacket> packets) {
  int option1, option2 = 0;

  for (int i = 0; i < packets.size(); i++) {
    if (packets[i].option == "2")
      option2++;
    if(packets[i].option == "1")
      option1++;
  }
  return option2 - option1;
}

bool isSpoofing (vector<arpPacket> packets) {
  return optionDirfference(packets) >= THRESHOLD;
}

// Write packets to file
vector<arpPacket> writePacketstoFile() {
  vector<arpPacket> packets;
  ifstream myFile;
  map<string, string> ARPtable;

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

int main() {
  vector<arpPacket> packets;
  packets = writePacketstoFile();
  isSpoofing(packets);
}
