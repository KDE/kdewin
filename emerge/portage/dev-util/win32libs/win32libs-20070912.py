import base
import os
import utils

SRC_URI= """
http://82.149.170.66/kde-windows/win32libs/zip/single/aspell-0.50.3-4-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/aspell-0.50.3-4-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/boost-headers-1.34-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/bzip2-1.0.4-4-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/bzip2-1.0.4-4-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/expat-2.0.1-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/expat-2.0.1-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/giflib-4.1.4-1-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/giflib-4.1.4-1-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/gpgme-1.1.4-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/gpgme-1.1.4-2-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/iconv-1.9.2-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/iconv-1.9.2-2-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/jasper-1.900.1-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/jasper-1.900.1-2-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/jpeg-6.b-5-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/jpeg-6.b-5-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/libintl-0.14.4-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libintl-0.14.4-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/libidn-1.1-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libidn-1.1-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/libpng-1.2.20-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libpng-1.2.20-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/libxml2-2.6.30-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libxml2-2.6.30-2-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/libxslt-1.1.22-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/libxslt-1.1.22-2-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/openslp-1.2.1-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/openslp-1.2.1-2-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/openssl-0.9.8e-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/openssl-0.9.8e-2-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/pcre-7.0-1-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/pcre-7.0-1-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/redland-1.0.3-3-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/redland-1.0.3-3-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/tiff-3.8.2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/tiff-3.8.2-lib.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/update-mime-database-0.21-6-bin.zip

http://82.149.170.66/kde-windows/win32libs/zip/single/zlib-1.2.3-2-bin.zip
http://82.149.170.66/kde-windows/win32libs/zip/single/zlib-1.2.3-2-lib.zip
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, SRC_URI )
    self.instdestdir = "win32libs"

  def compile(self):
    # here we need an own compile step, because we have to copy
    # the boost headers around, so that they are found for kdepimlibs
    srcdir  = os.path.join( self.workdir, "include", "boost-1_34" )
    destdir = os.path.join( self.workdir, "include", "boost-1_34_0" )
    utils.copySrcDirToDestDir( srcdir, destdir )
    return True

subclass().execute()
