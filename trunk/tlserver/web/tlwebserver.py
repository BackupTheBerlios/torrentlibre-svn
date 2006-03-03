import re
from os import curdir, sep
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer

pages = "pages"

class RequestHandler(BaseHTTPRequestHandler):

	def do_GET(self):
		if self.path == "/":
			self.path = "index.html"
		# to prevent parent dir reference
		p = re.compile('\/(\.){2,}')
		self.path = p.sub('', self.path)
		try:
			if self.path.endswith(".html"):
				f = open(curdir + sep + pages + sep + self.path)

				self.send_response(200)
				self.send_header('Content-type',	'text/html')
				self.end_headers()
				self.wfile.write(f.read())
				f.close()
				return
			else:
				raise IOError
				
		except IOError:
			self.send_error(404,'File Not Found: %s' % self.path)

def main():
	try:
		server = HTTPServer(('', 7998), RequestHandler)
		print 'tlwebserver started ...'
		server.serve_forever()
	except KeyboardInterrupt:
		print 'Abort by user'
		server.socket.close()

if __name__ == '__main__':
	main()
