---
title: Blog
layout: default
blog_index: true
---

<h1 class="page-title">{{ page.title }}</h1>

<ul>
    {% for post in site.posts %}
    {% unless post.draft == true or post.series %}
    <li class="post-item">
        <a class="post-title" href="{{ post.url }}">{{ post.title }}</a>
        <div class="post-date">
            <i>{{ post.date | date: '%B %-d, %Y' }}</i>
        </div>
    </li>
    {% endunless %}
    {% endfor %}
</ul>

