#pragma once
#include <async/task.hpp>
#include <backend/functional.hpp>
#include <backend/time.hpp>

namespace Constellation {
class IScheduler
{
  /// <summary>
  /// Post an action in the scheduler to be executed as soon as possible.
  /// </summary>
  /// <remarks>
  /// The action can be cancelled as long as the scheduler hasn't executed it.
  /// The method returns a task that completes once the action has been executed.
  /// </remarks>
  Task<void> postAsync(Func<void()> action, CancellationToken cancellationToken);

  /// <summary>
  /// Post an action in the scheduler to be executed after the specified delay.
  /// </summary>
  Task<void> postAsync(Func<void()> action, Milliseconds delay, CancellationToken cancellationToken);
};

class Schedulers
{
  /// <summary>
  /// Returns a scheduler that schedules actions on the main thread.
  /// </summary>
  static IScheduler main();
  /// <summary>
  /// returns a scheduler that schedules action on the thread pool.
  /// </summary>
  static IScheduler pool();
};
}// namespace Constellation