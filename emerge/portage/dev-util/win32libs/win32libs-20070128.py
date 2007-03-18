import base

#SRC_URI= "http://www.abi-neuhaus.de/chris/win32libs/win32libs-20070128.zip"

SRC_URI= """
http://82.149.170.66/kde-windows/win32libs/zip/complete/aspell-0.50.3-3.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/bzip2-1.0.4.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/expat-2.0.0.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/giflib-4.1.4.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/iconv-1.9.2.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/jasper-1.701.0.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/jpeg-6.b-4.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/libpng-1.2.15.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/libxslt-1.1.17.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/openssl-0.9.8d.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/pcre-7.0-1.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/tiff-3.8.0.zip
http://82.149.170.66/kde-windows/win32libs/zip/complete/zlib-1.2.3.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/libxml2-2.6.27-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libxml2-2.6.27-2-lib.zip
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instdestdir = "win32libs"
		
subclass().execute()
