/*
 * RuleOfFiveExample.h
 *
 *  Created on: Sep 20, 2017
 *      Author: mark
 */

#ifndef RULEOFFIVEEXAMPLE_H_
#define RULEOFFIVEEXAMPLE_H_

namespace mjl {
namespace homebrew {

class RuleOfFiveExample {
public:
	RuleOfFiveExample();
	RuleOfFiveExample(const RuleOfFiveExample&);
	RuleOfFiveExample(RuleOfFiveExample &&);
	const RuleOfFiveExample& operator=(const RuleOfFiveExample&);
	const RuleOfFiveExample& operator=(RuleOfFiveExample &&);
	virtual ~RuleOfFiveExample();
};

} /* namespace homebrew */
} /* namespace mjl */
#endif /* RULEOFFIVEEXAMPLE_H_ */

