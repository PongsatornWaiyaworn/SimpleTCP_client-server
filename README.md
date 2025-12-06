# TCP Square Calculator

โปรเจกต์นี้เป็นการสาธิตการใช้งาน **Windows Sockets (Winsock)** ในภาษา C/C++ เพื่อสร้างแอปพลิเคชัน Client/Server พื้นฐานบนระบบปฏิบัติการ Windows โดยมีวัตถุประสงค์หลักเพื่อให้บริการคำนวณฟังก์ชัน **กำลังสอง** ($f(x) = x^2$) ผ่านการเชื่อมต่อ TCP

ไคลเอนต์จะทำหน้าที่ส่งค่า **x** (ตัวเลขจำนวนเต็ม) ไปยังเซิร์ฟเวอร์ และเซิร์ฟเวอร์จะคำนวณผลลัพธ์ **$f(x)$** และส่งกลับมาให้ไคลเอนต์แสดงผล

## 🛠️ รายละเอียดทางเทคนิค

| รายละเอียด | ค่า |
| :--- | :--- |
| **ชื่อบริการ** | Square Calculator |
| **ภาษา** | C/C++ |
| **Networking API** | Winsock2 |
| **โปรโตคอล** | TCP (Transmission Control Protocol) |
| **พอร์ตมาตรฐาน** | 1235 |
| **ฟังก์ชันที่คำนวณ** | $f(x) = x^2$ |

## 📁 โครงสร้างไฟล์และหน้าที่

1.  **`server.cpp` (เซิร์ฟเวอร์):** ทำหน้าที่เป็น Listener บนพอร์ต 1235, รับค่า `x` ในรูปของไบนารี (`int`), คำนวณผลลัพธ์, และส่งกลับ
2.  **`client.cpp` (ไคลเอนต์):** ทำหน้าที่เชื่อมต่อไปยังเซิร์ฟเวอร์, รับพารามิเตอร์ hostname และค่า `x` จาก Command Line, ส่งค่า `x`, และแสดงผลลัพธ์ $f(x)$

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
