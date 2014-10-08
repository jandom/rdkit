// $Id$
//
//  Copyright (C) 2005-2006 Rational Discovery LLC
//
//   @@ All Rights Reserved @@
//  This file is part of the RDKit.
//  The contents are covered by the terms of the BSD license
//  which is included in the file license.txt, found at the root
//  of the RDKit source tree.
//

#include <boost/python.hpp>

#include <RDBoost/Wrap.h>
#include <GraphMol/GraphMol.h>

#include <RDCuda/hello-world.h>

namespace python = boost::python;


namespace RDKit {
  bool doHelloWorld(){

	  printf("%s\n","Before");
	  RDCuda::helloworld();
	  printf("%s\n","After");
  };

  bool doHelloMol(RDKit::ROMol &mol){

  	  printf("%s\n","Before");
  	  RDCuda::hellomol(mol);
  	  printf("%s\n","After");
    };

}

BOOST_PYTHON_MODULE(cuda)
{
	  python::scope().attr("__doc__") =
	    "Module containing functions for basic distance geometry operations"
	    ;

	  std::string docString;

	  docString = "Do triangle smoothing on a bounds matrix\n\n\
	 \n\
	 ARGUMENTS:\n\n\
	    - mat: a square Numeric array of doubles containing the bounds matrix, this matrix\n\
	           *is* modified by the smoothing\n\
	 \n\
	 RETURNS:\n\n\
	    a boolean indicating whether or not the smoothing worked.\n\
	\n";
	  python::def("helloworld", RDKit::doHelloWorld, docString.c_str());


	  docString = "empty";
	  python::def("hellomol", RDKit::doHelloMol, python::arg("mol"), docString.c_str());

}
