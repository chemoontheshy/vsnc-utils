#ifndef __VNSC_UTILS_TOKEN_H__
#define __VNSC_UTILS_TOKEN_H__
#include <iostream>
#include "../vsnc_utils.h"

namespace vsnc
{
	namespace utils
	{
		/**
		 * @brief 生成token参数，暂时只支持用户名和超时时间
		*/
		//struct TokenParam
		//{
		//	/**
		//	 * @brief 用户名
		//	*/
		//	std::string User;
		//	/**
		//	 * @brief 超时时间
		//	*/
		//	size_t      Expires;
		//	/**
		//	 * @brief 盐？
		//	*/
		//	std::string Token;
		//};

		/**
		 * @brief Token工具类
		*/
		class TokenUtils
		{
		public:
			/*
			*  默认析构函数
			*/
			~TokenUtils() = default;

			/**
			 * @brief token生成器
			 * @param user 签发用户
			 * @param expires 超时时间
			 * @return 返回token
			*/
			virtual const std::string CreateToken(const std::string& __VSNC_IN user, const size_t __VSNC_IN expires) noexcept = 0;


			/**
			 * @brief 验证token
			 * @param user 签发用户
			 * @param token token
			 * @return 0:验证成功，1:token过期、2、非法token
			*/
			virtual const size_t VerifyToken(const std::string& __VSNC_IN user, const std::string& __VSNC_IN token) noexcept = 0;
		};

		/**
		 * @brief 使用别名
		*/
		using   TokenUtilsPtr = std::shared_ptr<TokenUtils>;

		/**
		 * @brief 实例化Token工具类,方便实现单例模式
		*/
		class InstanceTUPtr
		{
		public:
			/**
			 * @brief 构造函数
			*/
			InstanceTUPtr();

			/**
			 * @brief 获取Token工具类指针
			 * @return Token工具类指针
			*/
			TokenUtilsPtr GetTokenUtilsPtr() { return m_pTokenUtils; }
		private:
			/**
			 * @brief Token工具类指针
			*/
			TokenUtilsPtr m_pTokenUtils;
		};

		/**
		 * @brief 实例化Token工具类单例
		*/
		typedef vsnc::utils::SingletonPtr<InstanceTUPtr> SingleTUPtr;
	}
}

#endif // !__VNSC_UTILS_TOKEN_H__

