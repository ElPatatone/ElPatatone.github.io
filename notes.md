---
layout: default
title: Notes 
---

<h1 class="page-title">{{ page.title }}</h1>

<ul>
  {% for note in site.notes %}
    <li class="post-item">
        <a href="{{ note.url }}">{{ note.name }}</a>
    </li>
  {% endfor %}
</ul>

