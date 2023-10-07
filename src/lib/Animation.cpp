#include "lib/Animation.hpp"

Animation::Animation()
    : ownership(new Animation::Inner()) {
}

Animation::Animation(AnimeStore const &animes)
    : ownership(new Animation::Inner()) {
  ownership->animes.assign(animes.begin(), animes.end());
}

Animation::Animation(usize const &anime_count)
    : ownership(new Animation::Inner()) {
  ownership->animes.resize(anime_count);
}

Animation::Animation(Animation const &rhs)
    : ownership() {
  *this = rhs;
}

Animation &Animation::operator=(Animation const &rhs) noexcept {
  if (this == &rhs) { return *this; }
  if (ownership != nullptr) { delete ownership; }
  ownership = rhs.ownership;
  const_cast<Animation &>(rhs).ownership = nullptr;
  return *this;
}

Animation::~Animation() noexcept {
  if (ownership != nullptr) { delete ownership; }
}

Animation Animation::clone() {
  Animation result(*this);
  if (result.ownership != nullptr) {
    ownership = new Animation::Inner();
    *ownership = *result.ownership;
  }
  return Animation(result);
}

usize Animation::getAnimeCount() const {
  this->ownershipCheck();
  return ownership->animes.size();
}

void Animation::setAnimeCount(usize const &anime_count) {
  this->ownershipCheck();
  ownership->animes.resize(anime_count);
}

usize Animation::getMotionCount(usize const &anime_code) const {
  this->codeCheck(anime_code);
  return ownership->animes[anime_code].size();
}

void Animation::setMotionCount(usize const &anime_code,
                               usize const &motion_count) {
  this->codeCheck(anime_code);
  ownership->animes[anime_code].resize(motion_count);
}

AnimeStore const &Animation::getAnimes() const {
  this->ownershipCheck();
  return ownership->animes;
}

void Animation::setAnimes(AnimeStore const &animes) {
  this->ownershipCheck();
  ownership->animes.assign(animes.begin(), animes.end());
}

Anime const &Animation::getAnime(usize const &anime_code) const {
  this->codeCheck(anime_code);
  return ownership->animes[anime_code];
}

void Animation::setAnime(usize const &anime_code, Anime const &anime) {
  this->codeCheck(anime_code);
  ownership->animes[anime_code].assign(anime.begin(), anime.end());
}

Motion const &Animation::getMotion(usize const &anime_code,
                                   usize const &motion_code) const {
  this->codeCheck(anime_code, motion_code);
  return ownership->animes[anime_code][motion_code];
}

void Animation::setMotion(usize const &anime_code,
                          usize const &motion_code,
                          Motion const &motion) {
  this->codeCheck(anime_code, motion_code);
  ownership->animes[anime_code][motion_code] = motion;
}

void Animation::ownershipCheck() const {
  if (ownership == nullptr) {
    throw std::runtime_error("No ownership rights whatsoever: Animation");
  }
}

void Animation::codeCheck(usize const &anime_code,
                          usize const &motion_code) const {
  this->ownershipCheck();
  if (anime_code >= ownership->animes.size()) {
    throw std::runtime_error("No exist anime_code.");
  } 
  if (motion_code != usize(-1) &&
      motion_code >= ownership->animes[anime_code].size()) {
    throw std::runtime_error("No exist motion_code.");
  }
}
