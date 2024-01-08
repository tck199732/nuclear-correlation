#ifndef HbtProperty_hpp
#define HbtProperty_hpp

#include <any>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

class HbtProperty {
public:
	HbtProperty() = default;
	HbtProperty(const HbtProperty &other) { this->mProperties = other.mProperties; }
	virtual ~HbtProperty() {
		for (auto &p : this->mProperties) {
			p.second.reset();
		}
		this->mProperties.clear();
	}

	template <typename T> void SetProperty(const std::string &key, const T &value) {
		// avoid setting unique_ptr to HbtProperty, check at compile time
		static_assert(
			!std::is_same_v<T, std::unique_ptr<std::remove_pointer_t<T>>>,
			"HbtProperty::SetProperty: unique_ptr is not allowed."
		);
		this->mProperties[key] = value;
	}

	/**
	 * @brief Get the HbtProperty object, keep the implementation in this header file to avoid linker
	 * problem.
	 */
	template <typename T> T GetProperty(const std::string &key) const {
		try {
			return std::any_cast<T>(this->mProperties.at(key));
		} catch (const std::bad_any_cast &e) {
			auto type = this->mProperties.at(key).type().name();
			std::string msg = e.what();
			msg = msg + " HbtProperty::GetProperty: key = " + key + ", type = " + type;
			msg = msg + ", expected type = " + typeid(T).name();
			throw std::invalid_argument(msg.c_str());

		} catch (const std::out_of_range &e) {
			throw std::out_of_range("HbtProperty::GetProperty: " + key + " not found.");
		}
		return T();
	}

	std::vector<std::string> GetKeys() const {
		std::vector<std::string> keys;
		for (auto &[key, _] : this->mProperties) {
			keys.push_back(key);
		}
		return keys;
	}

protected:
	std::map<std::string, std::any> mProperties;
};
#endif
