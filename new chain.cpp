#include <boost/assign/list_of.hpp>
#include <boost/array.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <share.h>
#if 0
class LTC_CTxMemPool : public CTxMemPool
{

  public:
    bool accept(CTxDB& txdb, CTransaction &tx, bool fCheckInputs, bool* pfMissingInputs);
    bool addUnchecked(const uint256& hash, CTransaction &tx);
    bool remove(CTransaction &tx);
    void queryHashes(std::vector<uint256>& vtxid);

};
#endif

class LTCBlock : public CBlock
{
public:
    // header
    static const int CURRENT_VERSION=4;
    static LTC_CTxMemPool mempool; 
    static CBlockIndex *pindexBest;
    static CBlockIndex *pindexGenesisBlock;
    static int64 nTimeBestReceived;

    LTCBlock()
    {
      ifaceIndex = LTC_COIN_IFACE;
      SetNull();
    }

    LTCBlock(const CBlock &block)
    {
      ifaceIndex = LTC_COIN_IFACE;
      SetNull();
      *((CBlock*)this) = block;
    }

    LTCBlock(const CBlockHeader &header)
    {
      ifaceIndex = LTC_COIN_IFACE;
      SetNull();
      *((CBlockHeader*)this) = header;
    }

    void SetNull()
    {
      nVersion = LTCBlock::CURRENT_VERSION;
      CBlock::SetNull();
    }

    void InvalidChainFound(CBlockIndex* pindexNew);
    unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast);
    bool AcceptBlock();
    bool IsBestChain();
    CScript GetCoinbaseFlags();
    bool AddToBlockIndex();
    bool CheckBlock();
    bool ReadBlock(uint64_t nHeight);
    bool ReadArchBlock(uint256 hash);
    bool IsOrphan();
    bool Truncate();
    bool VerifyCheckpoint(int nHeight);
    uint64_t GetTotalBlocksEstimate();


    int64_t GetBlockWeight();

		bool CreateCheckpoint(); 

		int GetAlgo() const { return (0); }


#ifdef USE_LEVELDB_COINDB
    bool SetBestChain(CTxDB& txdb, CBlockIndex* pindexNew);
    bool ConnectBlock(CTxDB& txdb, CBlockIndex* pindex);
    bool DisconnectBlock(CTxDB& txdb, CBlockIndex* pindex);
#else
    bool SetBestChain(CBlockIndex* pindexNew);
    bool ConnectBlock(CBlockIndex* pindex);
    bool DisconnectBlock(CBlockIndex* pindex);
#endif

//  protected: bool SetBestChainInner(CTxDB& txdb, CBlockIndex *pindexNew);
};



/**
 * A memory pool where an inventory of pending block transactions are stored.
 */
extern LTC_CTxMemPool LTC_mempool;

/**
 * The best known tail of the LTC block-chain.
 */
extern CBlockIndex* LTC_pindexBest;

/**
 * The initial block in the LTC block-chain's index reference.
 */
extern CBlockIndex* LTC_pindexGenesisBlock;

/**
 * The block hash of the initial block in the LTC block-chain.
 */
extern uint256 ltc_hashGenesisBlock;


extern int LTC_nBestHeight;
extern uint256 LTC_hashBestChain;
extern int64 LTC_nTimeBestReceived;

/**
 * Create a block template with pending inventoried transactions.
 */
CBlock* ltc_CreateNewBlock(const CPubKey& rkey);

/**
 * Generate the inital LTC block in the block-chain.
 */
bool ltc_CreateGenesisBlock();

/**
 * Set the best known block hash.
 */
bool ltc_SetBestChain(CBlock *block);

/**
 * Attempt to process an incoming block from a remote LTC coin service.
 */
bool ltc_ProcessBlock(CNode* pfrom, CBlock* pblock);

int64 ltc_GetBlockValue(int nHeight, int64 nFees);

CBlockIndex *ltc_GetLastCheckpoint();

bool ltc_IsOrphanBlock(const uint256& hash); 
void ltc_AddOrphanBlock(CBlock *block); 
void ltc_RemoveOrphanBlock(const uint256& hash); 
bool ltc_GetOrphanPrevHash(const uint256& hash, uint256& retPrevHash); 
CBlock *ltc_GetOrphanBlock(const uint256& hash); 
uint256 ltc_GetOrphanRoot(uint256 hash); 



/**
 * @}
 */

#endif /* ndef __LTC_BLOCK_H__ */
