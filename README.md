# end-task-communication-course

## מטלת סיום תקשורת

## 207867342 מגיש :דולב דובלון ת.ז

## הערות ותשובות לשאלות

## 1 בעיה

Send & receive udp

```
ולהראות שאני מבין את התוכנות לקמפל ולהריץ, להסביר מה קרה. 1
```
```
באמצעות הפקודה udpאנו פותחים שרת receive udp בקובץ
```
```
;socket_fd = socket (AF_INET, SOCK_DGRAM, 0)
```
## UDPמייצג פתיחת סוקת למטרת תיקשורת ב SOCK_DGRAM כאשר הדגל

## , מציע לנו בחירה אוטומטית של הפרוטוקול כמו שרשום. 0 כאשר הפרמטר האחרון שהוא

```
עבור שגיאה. 1 - עבור הסוקט החדש , או file descriptorהערך המוחזר הוא מספר ה
```
```
IP דגל שמייצג לכל הכתובות כאשר אין דרישה ספציפית ל INADDR_ANY
```
```
INADDR_ANY is used when you don't need to bind a socket to a specific IP. When you use this value as
.the address when calling bind(), the socket accepts connections to all the IPs of the machine
```
```
ולפורט הזה
```
```
(u_short)0x
```

```
fflushלאחר קונפיגורציה של משתני הסוקט , נבצע ניקוי של הטרמינל עם הפונקציה
```
```
s_inעל הסוקט לסטראקט bind נבצע
```
, שבעזרתה נדפיס recivfrom וניכנס ללואה אין סופית שבה נחכה לפאקטות שמתקבלות , באמצעות הפונקציה
msg את הקלט שמתקבל לתוך משתנה

```
receive udpסוף הסבר על //
```
```
send_udpהסבר על
```
## מתאימה IP, מבצעים השפה ל פורט המתאים ולכתובת ה UDPמאתחלים קונפיגרציות של סוקט של

```
sendto ולבסוף שולחים את ההודעה לפי הקונפיגורציה המתאימה באמצעות פקודת
```
```
בשורה השלישית הוא מתקבל בתור )ubuntu מעבירים לתוכנה פרמטר שהוא שם המחשב (אצלי זה היה
פונקציה מחזירה את מספר ה getpid() ,host שלוקחת את השם ומחליטה מי ה gethostbyname פרמטר ל
שרץ , המשמעות היא בשבילנו שנריץ כמה פעמים , שנדע איזה מספר התהליך שלנו. תהליך
```
```
ואותו אנו שולחים , כך נדע אם ה תהליך עדיין עובד כשנבדוק איזה תהליכים רצים במחשב.
```

```
printsin()לממש פונקציה חדשה. 2
```
```
שנעזרתי בהם manדפי
```
https://man7.org/linux/man-pages/man2/socket.2.html

https://man7.org/linux/man-pages/man7/socket.7.html

```
https://linux.die.net/man/2/recvfrom
```

## 2 בעיה

Data loss simulation

```
יצרתי את שלושת הקבצים,
```

## 3 בעיה

Use the files net_server.c and net_client.c and compile them review the programs to be sure •
you understand them

```
port 9999 מייצר שרת ב TCP קובץ של השרת ה
```
```
https://man7.org/linux/man-pages/man2/listen.2.html
```
```
מאזין ל חיבור אחד
```
```
accept()באמצעות חיבור קבלה של הן מתבצע שלב הלאחר מכ
```
```
https://man7.org/linux/man-pages/man2/accept4.2.html
```
## ואז מתבצעת שליחה

```
,שלנו connect socket על ה write באמצעות הפוקנציה קליינט ל מסויים של קאונטר
```
```
.ך המשתנה לא מוגדר פעמים א SIM_LENGTH מתבצעת הלולאה
```
## .את הסוקטים בסיום סוגרים

```
tcpשלבי הפעולה של שרת
```

```
net_client בקובץ
```
## ה וגם הוא פמוגדר LENGTH_SIM, המשתנה מוגדר IP אך ללא 1337 ל פורט TCPשל סוקט חיבור אנו מבצעים

## 10 מוגדר לערכו ל

```
sockaddr_inמה של הפורט ל סטראקט ברים לפונקציות להשהפרמטרים הנל מוע
```
```
.בייטים 4 גודל לסוקט , לקרוא ערך ב עשר פעמים read , ואז מבצעים קריאה tcp לפי שלבי connect מבצעים
```
Wget mimic


