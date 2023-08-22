#ifndef __VSNC_UTILS_TOKEN_IMPL_H__
#define __VSNC_UTILS_TOKEN_IMPL_H__
#include "vsnc_token.h"

namespace vsnc
{
	namespace utils
	{
		class TokenUtilsIMPL final : public TokenUtils
		{
		public:

			/**
			 * @brief token生成器
			 * @param user 签发用户
			 * @param expires 超时时间
			 * @return 返回token
			*/
			const std::string CreateToken(const std::string& __VSNC_IN user, const size_t __VSNC_IN expires) noexcept override;

			/**
			 * @brief 验证token
			 * @param user 签发用户
			 * @param token token
			 * @return 0:验证成功，1:token过期、2、非法token
			*/
			const size_t VerifyToken(const std::string& __VSNC_IN user, const std::string& __VSNC_IN token) noexcept override;
		};
	}
}

#endif // !__VSNC_UTILS_TOKEN_IMPL_H__

