# -*- coding: utf-8 -*-
"""
Created on Fri May 11 19:34:18 2018

@author: Sandeep
"""

import requests

response = requests.get('http://192.168.1.8/')

print(response.text)
