import base

DEPEND = """
virtual/base
dev-util/win32libs
kdesupport/kdewin32
kdesupport/qimageblitz
kdesupport/soprano
kdesupport/strigi
kde4-beta4/kdelibs-beta4
"""

class subclass(base.baseclass):
  def __init__(self):
    base.baseclass.__init__( self, "" )
    self.buildType = "RelWithDebInfo"
    self.instsrcdir = "kdenetwork"
    self.instdestdir = "kde"

  def unpack( self ):
    return self.kdeSvnUnpack( "tags/KDE/3.95/", "kdenetwork" )

  def compile( self ):
    return self.kdeCompile()

  def install( self ):
    return self.kdeInstall()

  def make_package( self ):
    return self.doPackaging( "kdenetwork", "3.95-1", True )

if __name__ == '__main__':
    subclass().execute()
