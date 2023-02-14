#ifndef CGFX_EVENTBUS_HPP
#define CGFX_EVENTBUS_HPP

#include <unordered_map>
#include <any>
#include <typeindex>
#include <functional>
#include <vector>
#include <memory>
#include "CGFX/Core/Macros.hpp"

namespace cgfx {

	struct EventBase {
	INTERFACE(EventBase);
	};

	namespace detail {
		struct IEventHandler {
		INTERFACE(IEventHandler);
		public:
			virtual void Handle(EventBase& event) const = 0;
		};

		template<typename EventT>
		struct EventHandler final : IEventHandler {
		public:
			explicit EventHandler(const std::function<void(EventT&)>& handler) : mHandler(handler) {

			}

			void Handle(EventBase& event) const override {
				auto& derived_event = static_cast<EventT&>(event);
				mHandler(derived_event);
			}

		private:
			std::function<void(EventT&)> mHandler;
		};
	}

	template<typename EventT> concept ValidEvent = std::is_base_of_v<EventBase, EventT>;

	class EventBus {
	public:

		template<typename EventT> requires ValidEvent<EventT>
		void Subscribe(const std::function<void(EventT&)>& callback) {
			auto callback_wrapper = std::make_unique<detail::EventHandler<EventT>>(callback);
			mCallbacks[typeid(EventT)].push_back(std::move(callback_wrapper));
		}

		template<typename EventT> requires ValidEvent<EventT>
		void Unsubscribe(const std::function<void(EventT&)>& callback) {
			//TODO Implement Unsubscribe
		}

		template<typename EventT, typename ...Args> requires ValidEvent<EventT>
		void Dispatch(Args&&... args) const {
			EventT event(std::forward<Args>(args)...);
			HandleAll(event, typeid(EventT));
		}

		void Dispatch(EventBase& event) const {
			HandleAll(event, typeid(event));
		}

	private:
		void HandleAll(EventBase& event, std::type_index type) const {
			if (!mCallbacks.contains(type)) {
				return;
			}
			const auto& callbacks = mCallbacks.at(type);
			for (const auto& callback: callbacks) {
				callback->Handle(event);
			}
		}

		std::unordered_map<std::type_index, std::vector<std::unique_ptr<detail::IEventHandler>>> mCallbacks;
	};

} // cgfx

#endif //CGFX_EVENTBUS_HPP
