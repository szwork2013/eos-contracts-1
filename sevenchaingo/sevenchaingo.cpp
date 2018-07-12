#include <eosiolib/eosio.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/print.hpp>
#include <vector>

using eosio::name;
using namespace eosio;
using namespace std;

class sevenchain : public eosio::contract
{//EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
   private:

   struct seven_account{
      account_name account;

      bytes hash;//64 bytes
      vector<uint64_t> random;
   };
   
   struct iteminfo{
      string name;
      uint64_t count;
   };

   public:
   using contract::contract;

   sevenchain(account_name self)
   :eosio::contract(self)
   {}


   //@abi action
   void startpoker(uint64_t id, const vector<struct seven_account> &participants, const vector<uint64_t> &rng)
   {
      //todo: participants count is 3
      //todo: seven_account's hash is 64 bytes
      //todo: rng count, seven_account random count is 52
   }

   //@abi action
   void startslot(uint64_t id, const vector<struct seven_account> &participants, const vector<uint64_t> &rng)
   {
      //todo: participants count is 3
      //todo: seven_account's hash is 64 bytes
      //todo: rng count, seven_account random count is 9
   }

   //@abi action
   void startitem(uint64_t id, const vector<struct seven_account> &participants, const vector<uint64_t> &rng)
   {
      //todo: participants count is 3
      //todo: seven_account's hash is 64 bytes
      //todo: rng count, seven_account random count is 9
   }

   //@abi action
   void saveiteminfo(const account_name id, const vector<struct iteminfo> &iteminfos)
   {
   }

};

EOSIO_ABI(sevenchain, (startpoker)(startslot)(startitem)(saveiteminfo))
