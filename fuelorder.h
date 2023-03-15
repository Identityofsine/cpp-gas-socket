
namespace Fuel{

    struct FuelType{
        unsigned int id = {};
        char* name;
        bool isDiesel = false;

        FuelType(){
            return;
        }

        FuelType(unsigned int _id){
            switch (_id)
            {
            case 0x01:
                name = "e87";
                break;
            case 0x02:
                name = "e89";
                break;
            case 0x03:
                name = "e89";
                break;
            case 0x04:
                name = "diesel";
                isDiesel = true;
                break;
            default:
                return;
            }
        }
    };

    class FuelOrder
        {
        private:
            /* data */
            int pump;
            double price;
            FuelType fueltype;

        public:
            FuelOrder();
            FuelOrder(FuelType ft, double price, int pump);
            ~FuelOrder();

            int getPump();
            double getPrice();
            FuelType getFuelType();
        };
    


}
