#ifndef property_hpp
#define property_hpp

#include <any>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

class property {
public:
	property() = default;
	property(const property &other) { this->properties = other.properties; }
	virtual ~property() {
		for (auto &p : this->properties) {
			p.second.reset();
		}
		this->properties.clear();
	}

	template <typename T> void set_property(const std::string &key, const T &value) {
		// avoid setting unique_ptr to property, check at compile time
		static_assert(
			!std::is_same_v<T, std::unique_ptr<std::remove_pointer_t<T>>>,
			"property::set_property: unique_ptr is not allowed."
		);
		this->properties[key] = value;
	}

	/**
	 * @brief Get the property object, keep the implementation in this header file to avoid linker
	 * problem.
	 */
	template <typename T> T get_property(const std::string &key) const {
		try {
			return std::any_cast<T>(this->properties.at(key));
		} catch (const std::bad_any_cast &e) {
			auto type = this->properties.at(key).type().name();
			std::string msg = e.what();
			msg = msg + " property::get_property: key = " + key + ", type = " + type;
			msg = msg + ", expected type = " + typeid(T).name();
			throw std::invalid_argument(msg.c_str());

		} catch (const std::out_of_range &e) {
			throw std::out_of_range("property::get_property: " + key + " not found.");
		}
		return T();
	}

	std::vector<std::string> get_keys() const {
		std::vector<std::string> keys;
		for (auto &[key, _] : this->properties) {
			keys.push_back(key);
		}
		return keys;
	}

protected:
	std::map<std::string, std::any> properties;
};
#endif
