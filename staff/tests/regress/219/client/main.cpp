// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Client skeleton

#include <iostream>
#include <memory>
#include <staff/utils/Log.h>
#include <staff/common/DataObject.h>
#include <staff/common/logoperators.h>
#include <staff/common/Exception.h>
#include "fooProxy.h"

using namespace staff;

int main(int /*nArgs*/, const char* /*paszArgs*/[])
{
  try
  {
      fooWebServiceProxy proxy;
      ::fooRequest fooRequest;

      fooRequest.fooRequest.attr1 = "value";
      fooRequest.fooRequest.commonTypeElement = "test";

      // here is the patched version of method, which returns the serialized request.
      staff::DataObject root = proxy.fooMethod(fooRequest);

      staff::LogInfo() << root.ToString();

      STAFF_ASSERT(root.GetNamespaceUri() == "http://ns/v1", "Wrong namespace for root");

      const staff::DataObject& child = root.FirstChild();
      STAFF_ASSERT(child.GetNamespaceUri() == "http://ns/v1", "Wrong namespace for child");

      const staff::DataObject& attr1 = child.FirstChild();
      STAFF_ASSERT(attr1.GetNamespaceUri() == "http://ns/v1", "Wrong namespace for attr1");

      const staff::DataObject& elem1 = attr1.NextSibling();
      STAFF_ASSERT(elem1.GetNamespaceUri() == "http://common/v1", "Wrong namespace for commonTypeElement");

      staff::LogInfo() << "namespaces are ok";

      //Normal exit (assert succeded)
      return 0;
  }
  STAFF_CATCH_ALL_DESCR("TEST FAILED")

  //Abnormal exit, exception thrown
//  return 3;
  return 0;
}
