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
		static_assert(!std::is_same_v<T, std::unique_ptr<std::remove_pointer_t<T>>>,
					  "property::set_property: unique_ptr is not allowed.");
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
			std::cerr << "property::get_property: " << e.what() << " of key : " << key << '\n';
			throw std::bad_any_cast();
		} catch (const std::out_of_range &e) {
			throw std::out_of_range("property::get_property: " + key + " not found.");
		}
		return T();
	}

protected:
	std::map<std::string, std::any> properties;
};
#endif
