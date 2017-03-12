#encoding utf-8
#!usr/local/bin/python

import sys
import MySQLdb
import urllib2
import hashlib

from sgmllib import SGMLParser

website = 'http://www.51cto.com/'
webname = '51cto'

class Record:
    def __init__(self, name, href):
        self.website = website
        self.websitename = webname
        self.name = name
#def sethref(self, href):
        self.href = href
        self.md5 = hashlib.md5(href).hexdigest()

class GetIdList(SGMLParser):
    def reset(self): 
        self.recordlist = []
        self.flag = False 
        self.getdata = False 
        self.verbatim = 0
        self.name = ""
        self.href = ""
        SGMLParser.reset(self) 
    def append(self, record):
       self.recordlist.append(record)
    def start_ul(self, attrs): 
        if self.flag == True:
            self.verbatim +=1
            return 
        for k,v in attrs:
            if k == 'class' and v == 'list':
		        self.flag = True
    def end_ul(self):
        if self.verbatim == 0: 
            self.flag = False 
        if self.flag == True:
            self.verbatim -=1

    def start_a(self, attrs):
        if self.flag == False:
            return
        for name, value in attrs:
            if name=='href':
                self.getdata = True
                self.href = value
            if name=='title':
                self.name = value
    def end_a(self):
        if self.getdata: 
            self.getdata = False 
    def handle_data(self, text):
        if self.getdata:
            if self.name.strip():
                self.append(Record(self.name, self.href))
            elif text.strip():
                self.append(Record(text, self.href))
    
    def printcontent(self): 
        for k in self.recordlist:
            print "--------------------"
            print k.website
            print k.name
            print k.href
            print k.md5
        print "record list size : %d " % len(self.recordlist)
    def insertdb(self):
        db = MySQLdb.connect("127.0.0.1","root","wlx8010040625","longyusoft")
        cursor = db.cursor()
        cursor.execute("SET NAMES utf8")
        cursor.execute("SET CHARACTER_SET_CLIENT=utf8")
        cursor.execute("SET CHARACTER_SET_RESULTS=utf8")
        db.commit()
        for record in self.recordlist:
            sql ="INSERT INTO longyusoft.longyu_link (title,url, from_website, from_url, md5, post_time) VALUES ('%s', '%s', '%s', '%s', '%s', now())" % (record.name.decode('gb2312').encode('utf8'), record.href, record.websitename, record.website, record.md5)
            cursor.execute(sql)
        db.commit()
        db.close()
        
def parserhtml():
    
    content = urllib2.urlopen(website).read()
    parser = GetIdList() 
    parser.feed(content)
#parser.printcontent()
    parser.insertdb()
    parser.close()

    print 'parser done!'
 
if __name__ == '__main__':
    parserhtml()
