#include "testbluetoothdevicelistmodel.cpp"
#include "testmoduleoptionsmodel.cpp"

int main(int argc, char **argv)
{
   int status = 0;

   {
      TestBluetoothDeviceListModel tc;
      status |= QTest::qExec(&tc, argc, argv);
   }

   {
      TestModuleOptionsModel tc;
      status |= QTest::qExec(&tc, argc, argv);
   }

   return status;
}
