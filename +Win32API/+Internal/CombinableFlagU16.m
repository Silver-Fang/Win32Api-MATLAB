classdef CombinableFlagU16<uint16
	%可组合的旗帜，支持使用运算符|进行按位组合，而不必使用bitor
	methods
		function C=or(A,B)
			C=bitor(A,B);
		end
	end
end