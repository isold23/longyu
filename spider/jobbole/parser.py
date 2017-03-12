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


website = 'http://blog.jobbole.com/'
webname = 'jobbole'

class Record:
    def __init__(self, name, href):
        self.website = website
        self.websitename = webname
        self.name = name
        self.href = href
        self.md5 = hashlib.md5(href).hexdigest()

class Parser(SGMLParser): 
   def reset(self): 
        self.recordlist = []
        self.flag = False
        self.getdata = False 
        self.verbatim = 0
        self.name = ""
        self.nameflag = False
        self.href = ""
        SGMLParser.reset(self) 
   def start_div(self, attrs): 
        if self.flag == True:
            self.verbatim +=1
            return 
        for k,v in attrs:
            if k=='class' and v=='post-meta':
                self.flag = True
   def end_div(self):
        if self.verbatim == 0: 
            self.flag = False 
        if self.flag == True:
            self.verbatim -=1
   
   def start_a(self, attrs):
        if self.flag == False:
           return
        for name, value in attrs:
            if name=='class' and value == 'meta-title':
                self.getdata = True
            if self.getdata:
                if name=='title':
                    self.name = value.decode('utf8').encode('gbk')
                    self.nameflag = True
                if name=='href':
                    self.href = value
   def end_a(self):
        if self.getdata: 
            self.getdata = False
            self.nameflag = False
   
   def handle_data(self, text):
        if self.getdata and self.nameflag: 
            self.recordlist.append(Record(self.name, self.href))
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
            sql ="INSERT INTO longyusoft.longyu_link (title,url, from_website, from_url, md5, post_time) VALUES ('%s', '%s', '%s', '%s', '%s', now())" % (record.name.decode('gbk').encode('utf8'), record.href, record.websitename, record.website, record.md5)
            cursor.execute(sql)
        db.commit()
        db.close()
        
    

def parserhtml():
    try:
        """
        httpHandler = urllib2.HTTPHandler(debuglevel=1)
        httpsHandler = urllib2.HTTPSHandler(debuglevel=1)
        opener = urllib2.build_opener(httpHandler, httpsHandler)
        urllib2.install_opener(opener)
        """
        content = urllib2.urlopen("http://blog.jobbole.com", timeout=10).read()
    except urllib2.HTTPError, e:
        print e.code
    parser = Parser() 
    parser.feed(content) 
#parser.printID()
    parser.insertdb()
    parser.close()
    print "done"
    
if __name__ == '__main__':
    parserhtml()
