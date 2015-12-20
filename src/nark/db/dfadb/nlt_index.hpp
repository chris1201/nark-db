#pragma once

#include <nark/db/data_index.hpp>
#include <nark/fsa/fsa.hpp>
#include <nark/int_vector.hpp>
#include <nark/rank_select.hpp>
#include <nark/fsa/nest_trie_dawg.hpp>

namespace nark {
//	class Nest
} // namespace nark

namespace nark { namespace db { namespace dfadb {

class NARK_DB_DLL NestLoudsTrieIndex : public ReadableIndex, public ReadableStore {
public:
	NestLoudsTrieIndex();
	~NestLoudsTrieIndex();

	///@{ ordered and unordered index
	llong numIndexRows() const override;
	llong indexStorageSize() const override;

	llong searchExact(fstring key, DbContext*) const override;
	bool  exists(fstring key, DbContext*) const;
	///@}

	IndexIterator* createIndexIterForward(DbContext*) const override;
	IndexIterator* createIndexIterBackward(DbContext*) const override;

	const ReadableStore* getReadableStore() const override;

	llong dataStorageSize() const override;
	llong numDataRows() const override;
	void getValueAppend(llong id, valvec<byte>* val, DbContext*) const override;
	StoreIterator* createStoreIterForward(DbContext*) const override;
	StoreIterator* createStoreIterBackward(DbContext*) const override;

	void build(SortableStrVec& strVec);
	void load(fstring path) override;
	void save(fstring path) const override;

protected:
//	std::unique_ptr<MatchingDFA> m_dfa;
	std::unique_ptr<NestLoudsTrieDAWG_SE_512> m_dfa;
	byte_t*     m_idmapBase;
	size_t      m_idmapSize;
	UintVecMin0 m_keyToId;
	UintVecMin0 m_idToKey;
	rank_select_se_512 m_recBits; // only for dupable index

	class UniqueIndexIterForward;   friend class UniqueIndexIterForward;
	class UniqueIndexIterBackward;	friend class UniqueIndexIterBackward;

	class DupableIndexIterForward;  friend class DupableIndexIterForward;
	class DupableIndexIterBackward;	friend class DupableIndexIterBackward;
};

}}} // namespace nark::db::dfadb
