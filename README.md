# TCP Square Calculator

โปรเจกต์นี้เป็นการสาธิตการใช้งาน **Windows Sockets (Winsock)** ในภาษา C/C++ เพื่อสร้างแอปพลิเคชัน Client/Server พื้นฐานบนระบบปฏิบัติการ Windows โดยมีวัตถุประสงค์หลักเพื่อให้บริการคำนวณฟังก์ชัน **กำลังสอง** ($f(x) = x^2$) ผ่านการเชื่อมต่อ TCP

ไคลเอนต์จะทำหน้าที่ส่งค่า **x** (ตัวเลขจำนวนเต็ม) ไปยังเซิร์ฟเวอร์ และเซิร์ฟเวอร์จะคำนวณผลลัพธ์ **$f(x)$** และส่งกลับมาให้ไคลเอนต์แสดงผล

## รายละเอียดทางเทคนิค

| รายละเอียด | ค่า |
| :--- | :--- |
| **ชื่อบริการ** | Square Calculator |
| **ภาษา** | C/C++ |
| **Networking API** | Winsock2 |
| **โปรโตคอล** | TCP (Transmission Control Protocol) |
| **พอร์ตมาตรฐาน** | 1235 |
| **ฟังก์ชันที่คำนวณ** | $f(x) = x^2$ |

## โครงสร้างไฟล์และหน้าที่

1.  **`server.cpp` (เซิร์ฟเวอร์):** ทำหน้าที่เป็น Listener บนพอร์ต 1235, รับค่า `x` ในรูปของไบนารี (`int`), คำนวณผลลัพธ์, และส่งกลับ
2.  **`client.cpp` (ไคลเอนต์):** ทำหน้าที่เชื่อมต่อไปยังเซิร์ฟเวอร์, รับพารามิเตอร์ hostname และค่า `x` จาก Command Line, ส่งค่า `x`, และแสดงผลลัพธ์ $f(x)$

## TCP Flow Diagram: Square Calculator (Client ↔ Server)

```text
Client                             Server
  |                                   |
  |--- SYN -------------------------->|
  |                                   |
  |<-- SYN-ACK -----------------------|
  |                                   |
  |--- ACK -------------------------->|
  |   (TCP Connection Established)    |
  |                                   |
  |--- send(x) ---------------------->|
  |        (send integer x)           |
  |                                   |
  |<-- ACK ---------------------------|
  |                                   |
  |<-- send(f(x)) --------------------|
  |       (Server computes x^2)       |
  |                                   |
  |--- ACK -------------------------->|
  |                                   |
  | (Client displays result)          |
  |                                   |
  |--- FIN -------------------------->|
  |                                   |
  |<-- FIN-ACK -----------------------|
  |                                   |
  |--- ACK -------------------------->|
  |                                   |
  (Connection Closed)
```

#### 1. TCP Handshake (3-way handshake)
- **Client ส่ง SYN → Server**  
  Client แจ้งว่าอยากเริ่มเชื่อมต่อ TCP
- **Server ตอบ SYN-ACK → Client**  
  Server ยืนยันว่าได้รับ SYN และพร้อมเชื่อมต่อ
- **Client ส่ง ACK → Server**  
  Client ยืนยันการเชื่อมต่อ
- **Result:** Connection Established

#### 2. Data Transfer
- **Client send(x) → Server**  
  Client ส่งค่า integer x ที่ต้องการคำนวณ
- **Server ACK และคำนวณ f(x) = x²**  
  Server รับค่า x, คำนวณผลลัพธ์
- **Server send(f(x)) → Client**  
  Server ส่งผลลัพธ์กลับไป Client
- **Client ACK และแสดงผล**  
  Client ยืนยันการรับผลลัพธ์และแสดงบนหน้าจอ

#### 3. Connection Termination (4-way handshake)
- **Client ส่ง FIN → Server**  
  Client แจ้งว่าจะปิดการเชื่อมต่อ
- **Server ส่ง FIN-ACK → Client**  
  Server ยืนยันและอาจส่ง FIN ของตัวเอง
- **Client ส่ง ACK → Server**  
  Client ยืนยันการปิด connection
- **Result:** Connection Closed

### TCP Flags Explanation

| Flag       | Full Name                   | ใช้ทำอะไร | ตัวอย่าง (Sequence / ACK) | คำอธิบาย |
|------------|----------------------------|------------|---------------------------|-----------|
| **SYN**   | Synchronize                | เริ่มต้น TCP connection | Client → Server : SYN seq=100 | Client แจ้งว่าอยากเริ่มเชื่อมต่อ TCP, มี sequence number เพื่อบอกตำแหน่งข้อมูลเริ่มต้น |
| **SYN-ACK** | Synchronize-Acknowledge    | ตอบรับ SYN และพร้อมเชื่อมต่อ | Server → Client : SYN seq=200, ACK=101 | Server ส่ง SYN ยืนยันตัวเองพร้อม ACK ยืนยันว่าได้รับ SYN ของ Client แล้ว (ACK = sequence number ของ client + 1) |
| **ACK**   | Acknowledge                | ยืนยันข้อมูลที่รับมา | Client → Server : ACK=201 | ใช้ยืนยันข้อมูลที่ส่งมาก่อนหน้านั้นถูกต้องครบถ้วน, หลัง handshake 3-way TCP connection ถูกสร้างเรียบร้อย |
| **FIN**   | Finish                     | เริ่มปิด TCP connection | Client → Server : FIN seq=300 | ฝั่งที่ส่ง FIN แจ้งว่าข้อมูลส่งหมดแล้ว ต้องการปิด connection |
| **FIN-ACK** | Finish-Acknowledge         | ยืนยันการปิด connection | Server → Client : FIN-ACK seq=400, ACK=301 | ฝั่งรับ FIN ตอบกลับเพื่อยืนยันการปิด connection, อาจส่ง FIN ของตัวเองพร้อมกัน |

## การคอมไพล์และการรันโปรแกรม

เนื่องจากโปรเจกต์นี้ใช้ **Winsock** คุณจำเป็นต้องคอมไพล์บนระบบ Windows โดยใช้คอมไพเลอร์ที่รองรับ เช่น **MinGW** หรือ **Visual Studio** และต้องลิงก์กับไลบรารี `ws2_32.lib`

## Compile Server & Client

Open your terminal and run the following commands:

```bash
# Compile the server
g++ server.cpp -o server -lws2_32

# Compile the client
g++ client.cpp -o client -lws2_32
```

## Running the Program
```bash
./server
```
```bash
#./client [hostname or IP address] [input value]
# ex.
./client localhost 5 
```
