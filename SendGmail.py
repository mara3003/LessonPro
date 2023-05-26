
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
import argparse
import os.path
import smtplib



parser = argparse.ArgumentParser(description="A simple calculator script")
parser.add_argument('receiverAddress')
parser.add_argument('studentName')
parser.add_argument('date')
parser.add_argument('hour')
parser.add_argument('subject')
parser.add_argument('teacherName')
args = parser.parse_args()
 
message = MIMEMultipart()
message["To"] = args.receiverAddress
message["From"] = 'LessonPro'
message["Subject"] = 'LessonPro Reminder'

with open(R'C:\Users\HOME\Desktop\LessonPro\logo-color.png', 'rb') as f:
    img = MIMEImage(f.read())
    img.add_header('Content-Disposition', 'attachment', filename='image.jpg')
message.attach(img)

title = '<b> Tomorrow lesson reminder </b>'
message_body=f"<br><br>Buna ziua,<br> {args.studentName} echipa LessonPro iti aduce aminte ca maine, {args.date}, de la ora {args.hour} ai programata o meditatie la {args.subject}  cu profesorul/profesoara {args.teacherName}. <br> Pentru modificarea meditatiei sau pentru intrebari suplimentare ne poti contacta la aceasta adresa de e-mail. <br> O zi buna!"
messageText = MIMEText(message_body,'html')
message.attach(messageText)



email = 'lessonprocontact@gmail.com'
password = 'mkfhhxjolzanoizf'

server = smtplib.SMTP('smtp.gmail.com:587')
server.ehlo('Gmail')
server.starttls()
server.login(email,password)
fromaddr = 'LessonPro'
toaddrs  = args.receiverAddress
server.sendmail(fromaddr,toaddrs,message.as_string())

server.quit()