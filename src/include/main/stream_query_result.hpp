//===----------------------------------------------------------------------===//
//                         DuckDB
//
// main/stream_query_result.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "main/query_result.hpp"

namespace duckdb {

class ClientContext;
class MaterializedQueryResult;

class StreamQueryResult : public QueryResult {
public:
	//! Create a successful StreamQueryResult. StreamQueryResults should always be successful initially (it makes no
	//! sense to stream an error).
	StreamQueryResult(ClientContext &context, vector<TypeId> types, vector<string> names);
	~StreamQueryResult() override;

	//! Fetches a DataChunk from the query result. Returns an empty chunk if the result is empty, or nullptr on error.
	unique_ptr<DataChunk> Fetch() override;
	//! Prints the QueryResult to the console
	void Print() override;
	//! Materializes the query result and turns it into a materialized query result
	unique_ptr<MaterializedQueryResult> Materialize();

	//! Closes the StreamQueryResult
	void Close();
	
	//! Whether or not the StreamQueryResult is still open
	bool is_open;
private:
	//! The client context this StreamQueryResult belongs to
	ClientContext &context;
};

} // namespace duckdb