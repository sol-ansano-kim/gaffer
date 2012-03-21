##########################################################################
#  
#  Copyright (c) 2012, Image Engine Design Inc. All rights reserved.
#  
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are
#  met:
#  
#      * Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#  
#      * Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials provided with
#        the distribution.
#  
#      * Neither the name of John Haddon nor the names of
#        any other contributors to this software may be used to endorse or
#        promote products derived from this software without specific prior
#        written permission.
#  
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
#  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#  
##########################################################################

import unittest

import IECore

import Gaffer

class ClassLoaderPathTest( unittest.TestCase ) :

	def test( self ) :
		
		p = Gaffer.ClassLoaderPath( IECore.ClassLoader.defaultOpLoader(), "/" )
		self.failUnless( p.isValid() )
		self.failIf( p.isLeaf() )
		
		p.append( "common" )
		self.failUnless( p.isValid() )
		self.failIf( p.isLeaf() )

		p.append( "iDontExist" )
		self.failIf( p.isValid() )
		self.failIf( p.isLeaf() )

		del p[-1]
		self.failUnless( p.isValid() )
		self.failIf( p.isLeaf() )

		p.setFromString( "/common/primitive/mesh/addNormals" )
		self.failUnless( p.isValid() )
		self.failUnless( p.isLeaf() )

		p.setFromString( "/common/primitive/mesh" )
		children = p.children()
		for child in children :
			self.failUnless( isinstance( child, Gaffer.ClassLoaderPath ) )
			self.assertEqual( len( child ), len( p ) + 1 )
			self.failUnless( child.isLeaf() )
			
		children = [ str( x ) for x in children ]
		self.failUnless( "/common/primitive/mesh/addNormals" in children )
		self.failUnless( "/common/primitive/mesh/addTangents" in children )
		self.failUnless( "/common/primitive/mesh/merge" in children )
		
		p.setFromString( "/" )
		children = p.children()
		for child in children :
			self.failUnless( isinstance( child, Gaffer.ClassLoaderPath ) )
			self.assertEqual( len( child ), len( p ) + 1 )
		
		p.setFromString( "/common/primitive/mesh/addNormals" )
		versions = p.info()["classLoader:versions"]
		self.failUnless( isinstance( versions, list ) )
		self.failUnless( len( versions ) )
		
	def testLoad( self ) :
	
		p = Gaffer.ClassLoaderPath( IECore.ClassLoader.defaultOpLoader(), "/common/primitive/mesh/addNormals" )
		
		op = p.load()()
		self.failUnless( isinstance( op, IECore.Op ) )
		
if __name__ == "__main__":
	unittest.main()
	