import base

SRC_URI= """
http://82.149.170.66/kde-windows/win32libs/zip/single/aspell-0.50.3-3-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/bzip2-1.0.4-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/bzip2-1.0.4-doc.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/bzip2-1.0.4-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/bzip2-1.0.4-src.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/expat-2.0.0-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/expat-2.0.0-doc.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/expat-2.0.0-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/expat-2.0.0-src.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/giflib-4.1.4-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/giflib-4.1.4-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/iconv-1.9.2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/iconv-1.9.2-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/jasper-1.701.0-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/jasper-1.701.0-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/jpeg-6.b-4-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/jpeg-6.b-4-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libintl-0.14.4-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libintl-0.14.4-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libpng-1.2.15-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libpng-1.2.15-doc.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libpng-1.2.15-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libpng-1.2.15-src.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libxml2-2.6.27-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libxml2-2.6.27-2-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libxslt-1.1.17-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libxslt-1.1.17-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/openssl-0.9.8d-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/openssl-0.9.8d-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/pcre-7.0-1-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/pcre-7.0-1-doc.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/pcre-7.0-1-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/pcre-7.0-1-src.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/tiff-3.8.0-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/tiff-3.8.0-lib.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/update-mime-database-0.20-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/zip-1.2.3-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/zip-1.2.3-lib.zip
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instdestdir = "win32libs"
		
subclass().execute()
