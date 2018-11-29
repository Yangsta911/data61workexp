import httplib2
import re
from setuptools.package_index import ContentChecker
from __builtin__ import int, str
def Get(b):
    if b == ('turn on relay 1'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay1_H')
    elif b == ('turn off relay 1'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay1_L')
    elif b == ('turn on relay 2'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay2_H')
    elif b == ('turn off relay 2'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay2_L')
    elif b == ('turn on relay 3'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay3_H')
    elif b == ('turn off relay 3'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay3_L')
    elif b == ('turn on relay 4'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay4_H')
    elif b == ('turn off relay 4'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay4_L')
    elif b == ('turn on relay 5'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay5_H')
    elif b == ('turn off relay 5'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay5_L')
    elif b == ('turn on relay 6'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay6_H')
    elif b == ('turn off relay 6'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay6_L')
    elif b == ('turn on relay 7'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay7_H')
    elif b == ('turn off relay 7'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay7_L')
    elif b == ('turn on relay 8'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay8_H')
    elif b == ('turn off relay 8'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/Relay8_L')
    elif b == ('check status'):
        h = httplib2.Http('.cache')
        content = h.request('http://relay01/status.html')
        a = content[1].split(' ')
        for str in a:
            print 'relay '+str+' is on'
        
        
    else:
        print('please enter turn on/off relay (number between 1-8) or check status')
while True:
    b = raw_input('Do you want to check status or turn on or off relays?: ') 
    Get(b)
    if b == ('quit'):
        break