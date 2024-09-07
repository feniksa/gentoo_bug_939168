#include <iostream>
#include "data.pb.h"

int main()
{
	serialize::Data data;
	data.set_link("ABC");
	auto keyValue = data.mutable_payload();
	keyValue->insert({"A_KEY", "A_VALUE"});
	keyValue->insert({"B_KEY", "B_VALUE"});
	keyValue->insert({"C_KEY", "C_VALUE"});

	const std::string serializedString = data.SerializeAsString();
	if (serializedString.empty()) {
		std::cerr << "issue with serialization\n";
		return -1;
	}

	// deserialize
	serialize::Data data2;
	bool ok = data2.ParseFromString(serializedString);
	if (!ok) {
		std::cerr << "issue with de-serialization\n";
		return -1;
	}

	return 0;
}
