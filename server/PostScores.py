import requests
import sys



requests.post("http://127.0.0.1:8000", data=sys.argv[1])