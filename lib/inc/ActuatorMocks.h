/*
 * Copyright 2013 Matthew McGowan
 * Copyright 2013 BrewPi/Elco Jacobs.
 *
 * This file is part of BrewPi.
 *
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>
#include "temperatureFormats.h"
#include "ActuatorInterfaces.h"
#include "ControllerMixins.h"

/*
 * A range actuator that simply remembers the set value. This is primary used for testing.
 */
class ActuatorValue final : public ActuatorRange, public ActuatorValueMixin
{
public:
    // construct without arguments, val = invalid, min and max are defaults
    ActuatorValue() : value(temp_t::invalid()), minimum(temp_t::min()), maximum(temp_t::max()){}

    // construct with just val, min and max are defaults
    ActuatorValue(temp_t initial) : value(initial), minimum(temp_t::min()), maximum(temp_t::max()){}

    // construct with val, min, max
    ActuatorValue(temp_t initial, temp_t minVal, temp_t maxVal) : value(initial), minimum(minVal), maximum(maxVal) {}

    ~ActuatorValue() = default;

    void setValue(temp_t const& val) override final {
        if(val < minimum){
            value = minimum;
        }
        else if(val > maximum){
            value = maximum;
        }
        else{
            value = val;
        }
    }
    temp_t getValue() const override final {
        return value;
    }

    virtual temp_t readValue() const override final {
    		return getValue();
    }


    void update() override final {}
    void fastUpdate() override final {}

    temp_t min() const override final {
        return minimum;
    }

    temp_t max() const override final {
        return maximum;
    }

private:
    temp_t value;
    temp_t minimum;
    temp_t maximum;

friend class ActuatorValueMixin;
};

/*
 * An toggle actuator that simply remembers a true/false set value. This is primary used for testing.
 */
class ActuatorBool final : public ActuatorDigital, public ActuatorBoolMixin
{
public:
    ActuatorBool() : state(false) {}
    ActuatorBool(bool initial) : state(initial) {}
    ~ActuatorBool() = default;

    void setActive(bool active) override final { state = active; }
    bool isActive() const override final { return state; }

    void update() override final {}
    void fastUpdate() override final {}

private:
    bool state;

friend class ActuatorBoolMixin;
};


/*
 * An digital actuators that does absolutely nothing. Used as default actuator
 */
class ActuatorNop final : public ActuatorDigital, public ActuatorNopMixin
{
public:
    ActuatorNop(){}
    ~ActuatorNop() = default;

    void setActive(bool active) override final {}
    bool isActive() const override final { return false;}
    void update() override final {}
    void fastUpdate() override final {}

friend class ActuatorNopMixin;
};

/*
 * An linear actuator that does nothing and always returns invalid(). Linear equivalent of ActuatorNop
 */
class ActuatorInvalid final : public ActuatorRange, public ActuatorInvalidMixin
{
public:
    ActuatorInvalid() {}
    ~ActuatorInvalid() = default;

    void setValue(temp_t const& val) override final {}
    temp_t getValue() const override final {
        return temp_t::invalid();
    }
    temp_t readValue() const override final {
        return temp_t::invalid();
    }
    temp_t min() const override final {
        return temp_t::invalid();
    }
    temp_t max() const override final {
        return temp_t::invalid();
    }
    void update() override final {}
    void fastUpdate() override final {}

friend class ActuatorInvalidMixin;
};
