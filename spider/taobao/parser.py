#encoding utf-8
#!usr/local/bin/python

import sys
#reload(sys)
#sys.setdefaultencoding('utf-8')

#import _mysql

import MySQLdb
import urllib2
import hashlib

from sgmllib import SGMLParser


website = 'http://www.searchtb.com/page/15'
webname = 'taobao'

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
   def start_h1(self, attrs): 
        if self.flag == True:
            self.verbatim +=1
            return 
        for k,v in attrs:
            if k == 'class' and v == 'prevtitle':
		self.flag = True
		return
   def end_h1(self):
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
                self.name = value
   def end_a(self):
        if self.getdata: 
            self.getdata = False 
   
   def handle_data(self, text):
        if self.getdata:
            self.append(Record(text, self.name))
   def printID(self): 
    for k in self.recordlist:
        print "--------------------"
        print k.website
        print k.name
        print k.href
        print k.md5

   def insertdb(self):
        
        db = MySQLdb.connect("127.0.0.1","root","wlx8010040625","longyusoft")
        cursor = db.cursor()
        cursor.execute("SET NAMES utf8")
        cursor.execute("SET CHARACTER_SET_CLIENT=utf8")
        cursor.execute("SET CHARACTER_SET_RESULTS=utf8")
        db.commit()
        for record in self.recordlist:
            sql ="INSERT INTO longyusoft.longyu_link (title,url, from_website, from_url, md5, post_time) VALUES ('%s', '%s', '%s', '%s', '%s', now())" % (record.name, record.href, record.websitename, record.website, record.md5)
            cursor.execute(sql)
        db.commit()
        db.close()
        
    

def parserhtml():
    
    content = urllib2.urlopen(website).read()
    parser = GetIdList() 
    parser.feed(content) 
    parser.printID()
    parser.insertdb()
    parser.close()
    print "done"
    
 
if __name__ == '__main__':
    parserhtml()
