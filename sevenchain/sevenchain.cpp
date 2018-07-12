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
      
      
      void print() const{
         eosio::print("account: ", account, "\nhash: ");
         for(auto byte : hash)
            eosio::print(byte, ",");
         eosio::print("\nrandom: ");
         for(auto n : random)
            eosio::print(n, ",");
         eosio::print("\n");
      }
   };
   
   //@abi table tableinfo
   struct tableinfo{
      uint64_t id;
      string tablename;
      uint64_t last_id;
      uint64_t count;

	   uint64_t primary_key()const { return id; }

      EOSLIB_SERIALIZE( tableinfo, (id)(tablename)(last_id)(count) )
   };

   //@abi table poker
   struct poker {
	   uint64_t id;

      vector<struct seven_account> participants;
      vector<uint64_t> rng;

	   uint64_t primary_key()const { return id; }
      
      EOSLIB_SERIALIZE( poker, (id)(participants)(rng) )
   };

   //@abi table slot
   struct slot {
	   uint64_t id;

      vector<struct seven_account> participants;
      vector<uint64_t> rng;

	   uint64_t primary_key()const { return id; }
      
      EOSLIB_SERIALIZE( slot, (id)(participants)(rng) )
   };
   
   //@abi table 
   struct item {
	   uint64_t id;

      vector<struct seven_account> participants;
      vector<uint64_t> rng;

	   uint64_t primary_key()const { return id; }
      
      EOSLIB_SERIALIZE( item, (id)(participants)(rng) )
   };

   struct iteminfo{
      string name;
      uint64_t count;
   };
   //@abi table itemcount
   struct itemcount{
	   account_name id;

      vector<struct iteminfo> items;

	   uint64_t primary_key()const { return id; }
 
      EOSLIB_SERIALIZE( itemcount, (id)(items))
   };

   typedef eosio::multi_index< N(tableinfo), tableinfo> tableinfos;
   tableinfos tables;

   typedef eosio::multi_index< N(poker), poker> poker_index;
   poker_index pokers;

   typedef eosio::multi_index< N(slot), slot> slot_index;
   slot_index slots;

   typedef eosio::multi_index< N(item), item> item_index;
   item_index items;

   typedef eosio::multi_index< N(itemcount), itemcount
     // ,indexed_by<N(byname), const_mem_fun<iteminfo, uint64_t, &iteminfo::primary_key>
      > itemcount_index;
   itemcount_index itemcounts;

   public:
   using contract::contract;

   sevenchain(account_name self)
   :eosio::contract(self)
   ,tables(_self, _self)
   ,pokers(_self, _self)
   ,slots(_self, _self)
   ,items(_self, _self)
   ,itemcounts(_self, _self)
   {}


   //@abi action
   void startpoker(uint64_t id, const vector<struct seven_account> &participants, const vector<uint64_t> &rng)
   {
      //todo: participants count is 3
      //todo: seven_account's hash is 64 bytes
      //todo: rng count, seven_account random count is 52
       auto poker_itr = pokers.emplace(_self, [&](auto& r){
           r.id = id;
           r.participants.assign(participants.begin(), participants.end());
           r.rng.assign(rng.begin(), rng.end());
       });

       auto info = tables.find(0);
       if(info == tables.end()) {
          tables.emplace(_self, [&](auto& r){
             r.id = 0;
             r.tablename = "poker";
             r.last_id = poker_itr->id;
             r.count = 1;
          });
       }else{
          tables.modify(info, _self,  [&](auto& r){
             r.last_id = poker_itr->id;
             r.count++;
          });
       }
       
   }

   //@abi action
   void startslot(uint64_t id, const vector<struct seven_account> &participants, const vector<uint64_t> &rng)
   {
      //todo: participants count is 3
      //todo: seven_account's hash is 64 bytes
      //todo: rng count, seven_account random count is 9
       auto slot_itr = slots.emplace(_self, [&](auto& r){
           r.id = id;
           r.participants.assign(participants.begin(), participants.end());
           r.rng.assign(rng.begin(), rng.end());
      });
       
       auto info = tables.find(1);
       if(info == tables.end()) {
          tables.emplace(_self, [&](auto& r){
             r.id = 1;
             r.tablename = "slot";
             r.last_id = slot_itr->id;
             r.count = 1;
          });
       }else{
          tables.modify(info, _self,  [&](auto& r){
             r.last_id = slot_itr->id;
             r.count++;
          });
       }
       
   }

   //@abi action
   void startitem(uint64_t id, const vector<struct seven_account> &participants, const vector<uint64_t> &rng)
   {
      //todo: participants count is 3
      //todo: seven_account's hash is 64 bytes
      //todo: rng count, seven_account random count is 9
       auto item_itr = items.emplace(_self, [&](auto& r){
           r.id = id;
           r.participants.assign(participants.begin(), participants.end());
           r.rng.assign(rng.begin(), rng.end());
      });
       
       auto info = tables.find(2);
       if(info == tables.end()) {
          tables.emplace(_self, [&](auto& r){
             r.id = 2;
             r.tablename = "item";
             r.last_id = item_itr->id;
             r.count = 1;
          });
       }else{
          tables.modify(info, _self,  [&](auto& r){
             r.last_id = item_itr->id;
             r.count++;
          });
       }
       
   }

   //@abi action
   void saveiteminfo(const account_name id, const vector<struct iteminfo> &iteminfos)
   {
      print(id,", ", N(id));
      auto it = itemcounts.find(id);
      if(it == itemcounts.end())
      {
         itemcounts.emplace(_self, [&](auto& r){
            r.id = id;
            r.items.assign(iteminfos.begin(), iteminfos.end());
         });
      }
      else{
         itemcounts.modify(it, _self, [&](auto& r){
            for(const auto& info : iteminfos)
            {
               bool exists = false;
               for(auto& dbinfo : r.items){
                  if(dbinfo.name == info.name)
                  {
                     dbinfo.count += info.count;
                     exists = true;
                     break;
                  }
               }
               if(exists == false)
                  r.items.push_back(info);
            }
         });
      }
   }

};

EOSIO_ABI(sevenchain, (startpoker)(startslot)(startitem)(saveiteminfo))
