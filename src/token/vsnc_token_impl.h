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
			 * @brief token������
			 * @param user ǩ���û�
			 * @param expires ��ʱʱ��
			 * @return ����token
			*/
			const std::string CreateToken(const std::string& __VSNC_IN user, const size_t __VSNC_IN expires) noexcept override;

			/**
			 * @brief ��֤token
			 * @param user ǩ���û�
			 * @param token token
			 * @return 0:��֤�ɹ���1:token���ڡ�2���Ƿ�token
			*/
			const size_t VerifyToken(const std::string& __VSNC_IN user, const std::string& __VSNC_IN token) noexcept override;
		};
	}
}

#endif // !__VSNC_UTILS_TOKEN_IMPL_H__

