
import http
from http.server import *
import socketserver

PORT = 8000

#run with python3 ScoresServer.py

class DoServerStuff(SimpleHTTPRequestHandler):
    def do_POST(self):
        self.send_response(200, "Success!")
        self.end_headers()
        httpData = self.rfile.read(int(self.headers['Content-Length'])).decode('ascii')

        with open("Scores.txt", "w") as f:
            f.write(httpData)

    def do_GET(self):
        with open("Scores.txt", "r") as f:
            self.send_response(200, "Success!")
            self.send_header("Content-type", "text/plain")
            self.end_headers()
            self.wfile.write(f.read().encode('ascii'))
        
with socketserver.TCPServer(("", PORT), DoServerStuff) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()




