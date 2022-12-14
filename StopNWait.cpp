#include <iostream>
#define MAX_PKT_SIZE 4
using namespace std;

typedef enum { dat, ack, nak } frameKind;
typedef enum { wait, frameArrival } eventType;

typedef struct{string data;} packet;

typedef struct { packet *info; frameKind kind; int seq; int ack;} frame;

class Protocol
{
public:
  int sentSeq;
  int receivedSeq;

  packet dataPkt;
  frame senderFrame, receiverFrame;

  Protocol()
  {
    sentSeq = receivedSeq = -1;
  }

  int waitForEvent(eventType e)
  {
    return e == frameArrival;
  }

  string showFrameKind(frameKind k)
  {
    switch (k)
    {
    case dat:
      return "Data";
      break;
    case ack:
      return "ACK";
      break;
    case nak:
      return "NAK";
      break;
    }
    return "";
  }

  // SENDER: Network -> Data Link Interface
  void fromNetworkLayer(packet &i)
  {
    cout << "\nEncapsulating Packet: '" << i.data << "'...";
    senderFrame.seq = ++sentSeq;
    senderFrame.kind = dat;
    senderFrame.info = &i;
  }

  // SENDER: Data Link -> Physical Interface
  void toPhysicalLayer(frame &f)
  {
    if (f.kind == dat)
      cout << "\nSending DataFrame [" << showFrameKind(f.kind) << ": " << f.seq << "] to Physical Layer...";
    else
      cout << "\nSending ControlFrame [" << showFrameKind(f.kind) << ": " << f.ack << "] to Physical Layer...";
  }

  // RECEIVER: Physical -> Data Link Interface
  void fromPhysicalLayer(frame &f)
  {
    cout << "\nReceived DataFrame [" << showFrameKind(f.kind) << ": " << f.seq << "] from Physical Layer...",
    cout << "\nValidating Sequence Number... ";
    if (receivedSeq != f.seq)
      cout << "\nDecapsulating Frame...";
    else
    {
      cout << "\nDuplicate Frame Encountered... Discarding Frame...";
    }
  }

  // RECEIVER: Data Link -> Network Interface
  void toNetworkLayer(packet &p)
  {
    cout << "\nSending Packet ['" << p.data << "'] to Network Layer...";
    receivedSeq = senderFrame.seq;
    receiverFrame.seq = 0;
    receiverFrame.kind = ack;
    receiverFrame.ack = senderFrame.seq + 1;
  }
};

class StopAndWaitARQ : public Protocol
{
public:
  string msg;
  eventType event;

  bool flag, start;
  int timeout_t, count, len, partSize;

  StopAndWaitARQ(string s, int t)
  {
    msg = s;
    timeout_t = t;
    partSize = 1e6;
    flag = false;
    start = false;
    count = 0;
  }

  void sender();
  void receiver();
};

void StopAndWaitARQ::sender()
{
  if (!start)
  {
    partSize = msg.length() % MAX_PKT_SIZE == 0
              ? msg.length() / MAX_PKT_SIZE
              : msg.length() / MAX_PKT_SIZE + 1;
    cout << "\nDividing data into groups of " << MAX_PKT_SIZE << " bits each.";
    start = !start;
  }

  cout << "\n\nSENDER\n----------";
  if (count > 0)
  {
    if (count % timeout_t == 0)
    {
      cout << "\nERR: TIMEOUT!";
      flag = true;
    }
    else
    {
      cout << "\nReceived ControlFrame ["<< showFrameKind(receiverFrame.kind) << ": " << receiverFrame.ack << "]...";
      if (flag)
      {
        count--;
        flag = !flag;
      }
    }
    if (receiverFrame.kind == nak || flag)
    {
      cout << "\nResending Previous Frame...";
      count--;
      flag = true;
    }
  }

  if (count == partSize)
  {
    cout << "\n\nData ['" << msg << "'] Sent Successfully.";
    exit(0);
  }

  while (count < partSize)
  {
    while (event != wait)
    {
      if (!flag)
      {
        dataPkt.data = "";
        cout << "\nEncapsulating [Data: " << count + 1 << "] into a Packet...";
        for (int i = 0; i < MAX_PKT_SIZE; i++)
          dataPkt.data += msg[i + count * MAX_PKT_SIZE];
        cout << "\nPassing Packet to Data Link Layer...";
        event = frameArrival;
      }
      if (waitForEvent(event))
      {
        if (!flag)
          fromNetworkLayer(dataPkt);
        toPhysicalLayer(senderFrame);
        event = wait;
      }
      receiver();
    }
  }
}

void StopAndWaitARQ::receiver()
{
  cout << "\n\nRECEIVER\n----------";
  if (event == wait)
  {
    fromPhysicalLayer(senderFrame);
    if (!flag)
    {
      toNetworkLayer(dataPkt);
      count++;
    }
    else
      count += 2;
    toPhysicalLayer(receiverFrame);
    event = frameArrival;
    sender();
  }
}

int main()
{
  string temp;
  cout << "\nEnter Data: ";
  getline(cin, temp);

  int temp2;
  cout << "Simulate noise at (>=2): ";
  cin >> temp2;

  StopAndWaitARQ *obj = new StopAndWaitARQ(temp, temp2);
  obj->sender();
  delete obj;

  cout << endl;
  return 0;
}
